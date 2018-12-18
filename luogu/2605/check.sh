g++ -g rand.cpp -o rand
g++ -g 2605.cpp -o 2605
g++ -g ans.cpp -o ans
while true ; do
    ./rand > rand.in
    ./2605	< rand.in > tyc.out 
    ./ans < rand.in > ans.out
    if diff tyc.out ans.out ; then
        printf "AC\n"
    else 
        printf "WA\n"
        exit
    fi
done
