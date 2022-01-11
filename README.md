Requirements:
 - **libcurl:** If not present install using

        sudo apt install libcurl4-openssl-dev
 - **openmp:**

Compile:
 - Parallel Pgm:

        gcc -o parallel -fopenmp parallel.c -lcurl
 - Serial Pgm:

        gcc -o serial serial.c -lcurl

To run:

    [serial/parallel] URL1 URl2 ...

        
