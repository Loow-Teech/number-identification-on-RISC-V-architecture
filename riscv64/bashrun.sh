export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib

for((i=1;i<11;i++)); do
echo -e \\n;
./main ./id/$i.jpg
done