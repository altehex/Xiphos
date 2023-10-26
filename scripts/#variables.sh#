CLANG_PATH=/usr/lib/clang
GCC_PATH=/usr/lib/gcc/x86_64-elf

PRINTF='printf'
ECHO='echo'

LIGHT_RED='\033[1;91m'
LIGHT_GREEN='\033[1;92m'
LIGHT_BLUE='\033[1;94m'

COLOR_END='\033[0m'

NOTIFY_SIGN="[${LIGHT_GREEN} ** ${COLOR_END}]"
PROMPT_SIGN="[${LIGHT_GREEN} ?? ${COLOR_END}]"
ERROR_SIGN="[${LIGHT_RED} !! ${COLOR_END}]"
OK_SIGN="[${LIGHT_GREEN} ++ ${COLOR_END}]"

XIPHOS="${LIGHT_BLUE}Xiphos${COLOR_END}"
VERSION_FMT="${LIGHT_GREEN}%s\n${COLOR_END}"
NOT_PRESENT="${LIGHT_RED}not present\n${COLOR_END}"

YES="[${LIGHT_GREEN}y${COLOR_END}] Yes"
NO="[${LIGHT_RED}n${COLOR_END}] No"

YES_DEFAULT="[${LIGHT_GREEN}Y${COLOR_END}] Yes"
NO_DEFAULT="[${LIGHT_RED}N${COLOR_END}] No"



pretty_line()
{
	if [[ -e /usr/bin/tput ]]; then
		
	   REPEAT=$((($(tput cols) - 2) / 3 - 1))
	   LINE="*"
	   while [[ $REPEAT -gt 0 ]]; do
		   LINE="${LINE}-+-"
		   REPEAT=$(($REPEAT - 1))
	   done
	   LINE="${LINE}*\n"
	   echo $LINE
	   
	elif [[ -z $COLUMNS ]]; then
		
		return ""
		
	else
		echo "*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-*\n"
	fi
    
}

PRETTY_LINE=`pretty_line`
