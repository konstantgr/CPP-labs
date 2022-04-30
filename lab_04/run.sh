iterations=1000000

echo ./build/threads_processes.out $iterations simple
./build/threads_processes.out $iterations simple
echo =================================

echo ./build/threads_processes.out $iterations threads
./build/threads_processes.out $iterations threads
echo =================================

num_processed=6
let "half = iterations/$num_processed"
for i in $(seq 1 $num_processed); 
do 
./build/threads_processes.out $half simple &
done

