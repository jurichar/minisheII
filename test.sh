# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[1;34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

make re
function test()
{
	echo "" > DIF
	echo $BLUE"> "$RESET$@"; exit" > RESULT1
	echo $@"; exit" | ./minishell > RESULT2
	echo $@"; exit" | bash >> RESULT1
	diff RESULT1 RESULT2 > DIF
	RES=$(cat DIF)

	if [ !$RES ]; then
		echo $GREEN"OK"$RESET
	else
		echo $RED"FAILURE ON: $RESET$@"
		echo Your output : > DIF
		cat RESULT2 >> DIF
		echo \n >> DIF
		echo Expected output : >> DIF
		cat RESULT1 >> DIF
		echo \n >> DIF
	fi
	sleep 0.1
}

# ECHO
echo $BOLDBLUE"TEST ECHO:"$RESET
test 'echo oui'
test 'echo -n -n -nnnn -nnnnm ; echo a'
test 'echo -n -nnn hello -n ; echo a'
test 'echo ~'
# PWD
echo $BOLDBLUE"\nTEST PWD:"$RESET
test 'pwd'

# CD
echo $BOLDBLUE"\nTEST CD:"$RESET
test 'cd .. ; pwd'
test 'cd .. ; cd .. ; pwd'
test 'cd ../../../../../.. ; pwd'
test 'cd /Users/lebourre/ ; pwd'
test 'cd $HOME/Desktop ; pwd'
test 'cd - ; pwd'
# EXEC
echo $BOLDBLUE"\nTEST ';':"$RESET
test 'ls ; ls'
test 'ls ; ls ; ls ; ls ; ls ; ls'

#EXIT STATUS
echo $BOLDBLUE"\nTEST EXIT STATUS:"$RESET
test 'cd random_cmd ; echo $?'
test 'cd random_cmd ; cd $?'
test './file_that_is_not_an_executable'
test 'cat bla'
test 'file_name'
test 'export test=a ; echo $test'
test 'ls bonjour ; echo $?'

# EXPORT
#test 'echo $$'
