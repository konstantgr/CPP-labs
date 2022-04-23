iterations=10000

echo ./build/threads_processes.out $iterations simple
./build/threads_processes.out $iterations simple

echo ./build/threads_processes.out $iterations threads
./build/threads_processes.out $iterations threads

let "half = iterations/2"
echo ./build/threads_processes.out $half threads TWICE
./build/threads_processes.out $half simple &
./build/threads_processes.out $half simple &
