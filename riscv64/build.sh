export PATH=$PATH:/opt/riscv/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/riscv/openriscv/include
#export LD_LIBRARY_PATH="/usr/local/riscv/openriscv/lib:$LD_LIBRARY_PATH"
riscv64-unknown-linux-gnu-g++ /home/tbh/Desktop/fkcv/batch_proc/main.cpp  -o /home/tbh/Desktop/fkcv/batch_proc/main -I /usr/local/riscv/openriscv/include/opencv4 -L /usr/local/riscv/openriscv/lib -lopencv_core  -lopencv_imgcodecs -lopencv_imgproc
