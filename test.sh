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
	TEST=$(cat DIF)

	if [ !$TEST ]; then
		printf "YES"
	else
		printf "NOP"
		echo
		printf "Your output :" 
		cat RESULT2
		echo "\n"
		printf "Expected output :"
		cat RESULT1
		echo "\n"
	fi
	echo
	sleep 0.1
}

# ECHO
test 'echo oui'
test 'echo oui     non'
test 'echo -n coucou'
test 'echo -nm coucou'
test 'echo -mmmmn coucou'

# PWD
test 'pwd'

# CD
test 'cd .. ; pwd'
test 'cd .. ; cd .. ; pwd'

# ENV
test 'env'

# EXEC
test 'ls ; ls'
test 'ls ; ls ; ls ; ls ; ls ; ls'

# EXPORT
#test 'echo $$'