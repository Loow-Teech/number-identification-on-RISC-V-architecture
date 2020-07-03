export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib

ftp -i -v -n 192.168.123.109  <<EOF
user anonymous 1
binary
cd /1/
lcd ./id/
get logoword.jpg
bye
EOF
 
rm -rf ./result.txt
for((i=1;i<11;i++)); do
echo -e \\n;
./main ./id/$i.jpg
done

ftp -i -v -n 192.168.123.109  <<EOF
user anonymous 1
binary
put result.txt
bye
EOF
