extension=".tk"
result=".rs"

progressBarWidth=50

# Function to draw progress bar
progressBar () {

  # Calculate number of fill/empty slots in the bar
  progress=$(echo "$progressBarWidth/$taskCount*$tasksDone" | bc -l)  
  fill=$(printf "%.0f\n" $progress)
  
  if [ $fill -gt $progressBarWidth ]; then
    fill=$progressBarWidth
  fi
  empty=$(($fill-$progressBarWidth))

  # Percentage Calculation
  percent=$(echo "100/$taskCount*$tasksDone" | bc -l)
  percent=$(printf "%0.2f\n" $percent)
  if [ $(echo "$percent>100" | bc) -gt 0 ]; then
    percent="100.00"
  fi

  # Output to screen
  printf "\33[2K\r["
  
  printf "%${fill}s" '' | tr ' ' ░
  printf "%${empty}s" '' | tr ' ' - 
  printf "] $percent%% - $f "
}



## Collect task count
taskCount=150
tasksDone=0

# for f in code/**/*.cpp  ; do
#   sed -i -e '$a\' $f
#   ./cppTokeniser.exe < $f > $f$extension
#   (( tasksDone += 1 ))
#   progressBar $taskCount $taskDone $f
# done;

for f in code/**/*.cpp.tk.rs  ; do
  sed -i -e '$a\' $f
  echo "Begin" > $f
done;

tasksDone=0
progressBar $taskCount $taskDone $f
for f in code/**/*.cpp.tk  ; do
    echo "Comparing: " $f >> $f$result
    for h in code/**/*.cpp.tk  ; do
      sed -i -e '$a\' $h 
      ./TokenComparer.exe $f $h >> $f$result
    done; 
    (( tasksDone += 1 ))
    progressBar $taskCount $taskDone 
    #printf "$f"
done;



# for f in code/**/*.cpp  ; do
#   for h in code/**/*.cpp  ; do
#     echo $h >> temp
#     sed -i -e '$a\' $h    
#   done;
#   echo $f
#   (( tasksDone += 1 ))
#   progressBar $taskCount $taskDone $text
#   sed -i -e '$a\' $f
#   ./cppTokeniser.exe < $f > $f$extension
# done;