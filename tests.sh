touch make_output.txt time.txt temp_results.txt
make clean > make_output.txt
cp main.c previous_main_backup.c
make normal >> make_output.txt
TIMEFORMAT="Time: %0lR"

clean_and_exit () {
  echo "-------- TEST: Exiting"

  cp previous_main_backup.c main.c
  make clean >> make_output.txt
  rm make_output.txt temp_results.txt time.txt previous_main_backup.c
  exit 0
}

test_setup () {
  cp $CURRENT_MAIN temp_main.c
  make clean > make_output.txt
  make >> make_output.txt
  score_reset 0
}

subcase_test () {
  CORRECT_RESULT=${CORRECT_RESULT_ARR[NTESTS]}
  NTESTS=`expr $NTESTS + 1`
  { time (./test < $CURRENT_DATA_DIR/$FILE > temp_results.txt); } 2> time.txt
  TIME_ELAPSED=`cat time.txt`
  if [ "$TIME_ELAPSED" == "Time: 0m0s" ]
  then
    echo -e "\e[4;39mTime: < 1s\e[0m"
  else
    echo -e "\e[4;39m$TIME_ELAPSED\e[0m"
  fi
  read -a RESULTS_ARRAY < temp_results.txt
  CURRENT_RES=${RESULTS_ARRAY[0]}
}

subcase_result_show () {
  if test "$CURRENT_RES" -eq "$CORRECT_RESULT"
    then
      echo -e "\e[1;32m---------------- PASSED: $TESTNAME OK\e[0m"
      SCORE=`expr $SCORE + 1`
    else
      echo -e "\e[1;31m---------------- ERROR: $TESTNAME returned $CURRENT_RES but should return "$CORRECT_RESULT"\e[0m"
  fi
}

score_reset () {
  SCORE=0
  NTESTS=0  
}

score_show () {
  TOTALSCORE=`echo "scale=2; ($SCORE / $NTESTS) * 100" |bc -l`
  echo "TOTAL SCORE is $TOTALSCORE%"
}

###############################################################################

greedy_test () {
  echo -e "\e[1;33m-------- TESTING GREEDY\e[0m"
  CURRENT_MAIN="main_for_greedy.c"
  CURRENT_DATA_DIR="greedy_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=(4 16 21 42 42 339 77 6 100 500 1000)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="Greedy on $FILE"
    subcase_test 0
    subcase_result_show 0 
  done

  score_show 0
}

###############################################################################

welsh_powell_test () {
  echo -e "\e[1;33m-------- TESTING WELSH POWELL\e[0m"
  CURRENT_MAIN="main_for_welshpowell.c"
  CURRENT_DATA_DIR=welshpowell_test_data
  test_setup 0

  CORRECT_RESULT_ARR=(17 23 34 34 264 97 239 581 5 2099)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="Welsh Powell and Greedy on $FILE"
    subcase_test 0
    subcase_result_show 0
  done

  score_show 0
}

###############################################################################

bipartito_test () {
  echo -e "\e[1;33m-------- TESTING BIPARTITO\e[0m"
  CURRENT_MAIN="main_for_bipartito.c"
  CURRENT_DATA_DIR="bipartito_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=('0' '0' '0' '0' '0' '0' '0' '0' '0' '1' '1' '1' '0' '0' '0')
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="Bipartito on $FILE"
    subcase_test 0    
    subcase_result_show 0
  done

  score_show 0
}

###############################################################################

numCCs_test () {
  echo -e "\e[1;33m-------- TESTING NumCCs\e[0m"
  CURRENT_MAIN="main_for_NumCCs.c"
  CURRENT_DATA_DIR="numCCs_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=(1 3 3 3 3 1 1 1 1 1 9)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="NumCCs on $FILE"
    subcase_test 0
    subcase_result_show 0
  done

  score_show 0
}

chicoGrande_test () {
  echo -e "\e[1;33m-------- TESTING ChicoGrande\e[0m"
  CURRENT_MAIN="mains/main_for_chicogrande.c"
  CURRENT_DATA_DIR="chicogrande_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="ChicoGrande on $FILE"
    subcase_test 0
    subcase_result_show 0
  done

  score_show 0
}

aleatorizarVert_test () {
  echo -e "\e[1;33m-------- TESTING Aleatorizar Vertices\e[0m"
  CURRENT_MAIN="main_for_aleatvert.c"
  CURRENT_DATA_DIR="chicogrande_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="AleatorizarVertices on $FILE"
    subcase_test 0
    subcase_result_show 0
  done

  score_show 0
}

switchColores_test () {
  echo -e "\e[1;33m-------- TESTING Switch Colores\e[0m"
  CURRENT_MAIN="main_for_switchcolores.c"
  CURRENT_DATA_DIR="chicogrande_test_data"
  test_setup 0

  CORRECT_RESULT_ARR=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
  for FILE in `ls $CURRENT_DATA_DIR | sort -V`; do
    TESTNAME="SwitchColores on $FILE"
    subcase_test 0
    subcase_result_show 0
  done

  score_show 0
}

###############################################################################

if [ $# == 0 ]
then
  greedy_test 0
  echo ""
  welsh_powell_test 0
  echo ""
  bipartito_test 0
  echo ""
  numCCs_test 0
  echo ""
  chicoGrande_test 0
  echo ""
  aleatorizarVert_test 0
  echo ""
  switchColores_test 0
elif [ $1 == "greedy" ]
then
  greedy_test 0
elif [ $1 == "wp" ]
then
  welsh_powell_test 0
elif [ $1 == "bip" ]
then
  bipartito_test 0
elif [ $1 == "cc" ]
then
  numCCs_test 0
elif [ $1 == "cg" ]
then
  chicoGrande_test 0
elif [ $1 == "av" ]
then 
  aleatorizarVert_test 0
elif [ $1 == "sc" ]
then
  switchColores_test 0
fi


echo "-------- TEST: All test done"

clean_and_exit 0
