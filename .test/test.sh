#!/bin/bash

ipcclean() {
    ipcs -q | awk '($$2~/^[0-9]+$$/) { system("ipcrm -q " $$2) }'
    ipcs -m | awk '($$2~/^[0-9]+$$/) { system("ipcrm -m " $$2) }'
    ipcs -s | awk '($$2~/^[0-9]+$$/) { system("ipcrm -s " $$2) }'
}

failure() {

    ipcclean

    FEEDBACK+=":x: L'esercizio non è ancora stato svolto correttamente.\n"
    FEEDBACK+=":warning: $1 :warning:\n"

    printf "$FEEDBACK" >> $FEEDBACKFILE_PATH


    # More detailed feedback
    if [ $# -eq 2 ]
    then
        cat $2 >> $FEEDBACKFILE_PATH
    fi


    echo "fail"
    exit 1
}

format_semgrep_json() {

    JSON=$1

    OUTPUT_FILE=/tmp/semgrep_formatted.md

    printf "\n\n" > $OUTPUT_FILE

    NUM_RESULTS=`jq '.results|length' $JSON`

    for I in $(seq 0 $((${NUM_RESULTS}-1)))
    do
        printf "<i>" >> $OUTPUT_FILE
        jq -r ".results[$I].extra.message" $JSON >> $OUTPUT_FILE
        printf "</i>\n" >> $OUTPUT_FILE
        printf "(codice errore: "$(jq -r ".results[$I].check_id" $JSON)")\n" >> $OUTPUT_FILE
        printf "\n\n\`\`\`\n" >> $OUTPUT_FILE
        jq -r ".results[$I].extra.lines" $JSON >> $OUTPUT_FILE
        printf "\n\`\`\`\n\n\n\n" >> $OUTPUT_FILE
    done

    echo ${OUTPUT_FILE}
}


function compile_and_run() {

    BINARY=$1
    OUTPUT=$2
    TIMEOUT=$3
    MAKE_RULE=$4

    cd $SOURCEDIR

    if ! make ${MAKE_RULE} >/dev/null;
    then
        failure "Non è stato possibile compilare il programma"
    fi



    rm -f $OUTPUT
    ipcclean

    IPC_BEFORE=$(ipcs | grep -c "0x")

    if ! unbuffer timeout $TIMEOUT ./$BINARY > $OUTPUT;
    then
        failure "L'esecuzione del programma non termina correttamente"
    fi

    cd - > /dev/null

    IPC_AFTER=$(ipcs | grep -c "0x")

    if [[ $IPC_BEFORE != $IPC_AFTER ]]
    then
        failure "È necessario deallocare le risorse IPC al termine della esecuzione"
    fi

}


function static_analysis() {

    CONFIG_FILES=("$@")

    if [ ${#CONFIG_FILES[@]} -eq 0 ]
    then
        CONFIG_FILES=($TESTDIR/*.yml)
    fi


    JSON_SEMGREP=/tmp/semgrep.json

    for CONFIG in "${CONFIG_FILES[@]}"
    do

        SOURCEPATH=$SOURCEDIR/$(basename $CONFIG .yml)".c"
        SOURCE=$(basename $SOURCEPATH)


        PREPROCESSED=$SOURCEDIR/$(basename $SOURCE .c)".preprocessed.c"
        cp $SOURCEPATH $PREPROCESSED


        # Pre-process the source file (#define, #include)

        cd $SOURCEDIR

        PREPROCESSOR=../.test/preprocessor.pl

        $PREPROCESSOR $PREPROCESSED

        cd - > /dev/null


        # Run semgrep

        env NO_COLOR=1 semgrep --error --quiet  --json --max-lines-per-finding 50 --config $CONFIG $PREPROCESSED -o $JSON_SEMGREP

        if [ $? -ne 0 ]
        then

            SEMGREP_MD=$(format_semgrep_json "$JSON_SEMGREP")

            rm $PREPROCESSED

            failure "Anche se il programma esegue, sono stati riscontrati i seguenti difetti all'interno del codice ($SOURCE)" "${SEMGREP_MD}"

        fi

        rm $PREPROCESSED

    done
}


function success() {

    FEEDBACK+=":white_check_mark: Congratulazioni, l'esercizio compila ed esegue correttamente, e non è stato riscontrato nessuno degli errori frequenti nel codice :tada:\n"

    printf "$FEEDBACK" >> $FEEDBACKFILE_PATH

    echo "pass"
    exit 0
}


function skipped() {

    FEEDBACK+=":fast_forward: La verifica automatica è stata disattivata per questo esercizio\n"

    printf "$FEEDBACK" >> $FEEDBACKFILE_PATH

    echo "pass"
    exit 0
}


function init_feedback() {

    MSG=$1

    FEEDBACK="\n## $MSG\n\n"

    if [[ $SKIPPED != 0 ]]
    then
        skipped
    fi
}


export TESTDIR="$(realpath $(dirname "$0"))"
export SOURCEDIR=$TESTDIR/..

export FEEDBACKFILE_PATH=/tmp/feedback.md
export FEEDBACK=

export SKIPPED=0

