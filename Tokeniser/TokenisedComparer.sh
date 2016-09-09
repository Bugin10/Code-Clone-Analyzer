extension=".tk"
for f in code/**/*.cpp  ; do
  echo $f
  sed -i -e '$a\' $f
  ./cppTokeniser.exe < $f > $f$extension
done;