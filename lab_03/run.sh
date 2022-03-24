for action in + - ^
do
echo ./build/calc.out  13 $action 3
./build/calc.out 13 $action 3  
done

echo ./build/hanoi.out
./build/hanoi.out
