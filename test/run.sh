if [ -z "$1" ]; then
	echo "missing parameter"
	exit
fi

echo "Generating unsolvable puzzles"
for i in {1..50}; do python puzzle_generator.py "$1" -u  > u"$i";done
#echo "Generating solvable puzzles"
#for i in {1..50}; do python puzzle_generator.py "$1" -s  > s"$i";done

echo "\033[0;31mNot solvable test\033[0m"
for i in {1..50}; do ../n-puzzle u"$i";done
#echo "\033[0;31mSolvable test\033[0m"
#for i in {1..50}; do ../n-puzzle s"$i";done

