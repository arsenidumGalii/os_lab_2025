AVERAGE=0
COUNT=$#
for arg in "$@"
do
	number=$((arg))
	AVERAGE=$((AVERAGE+number))
done
AVERAGE=$((AVERAGE/COUNT))
echo "Count: $#"
echo "Average: $AVERAGE"