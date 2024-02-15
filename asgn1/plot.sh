#plot.sh

#!/ bin / bash

make clean
make monte_carlo

#graph 1
#run monte carlo and store cols x y and circle to dat file
./monte_carlo -n 1000 | awk {'print $3, $4, $5'} > /tmp/graph.dat
#ignore line 1 as titles
#plot the black line with a circle object
#plot of x and y from dat file with palette for in and out of circle
#if in circle is 0, right of line and red
#if in circle is 1, left of line and blue
gnuplot <<END
    set terminal pdf
    set output "graph1.pdf"
    set title "Monte Carlo"
    set xlabel "x"
    set ylabel "y"
    set zeroaxis
    set xrange [0:1]
    set yrange [0:1]
    set size square
    set key autotitle columnhead
    set palette defined (0 "red", 1 "blue")
    unset colorbox
    set object 1 circle at 0,0 size 1
    plot "/tmp/graph.dat" with dots palette notitle
END

#graph 2
#run monte carlo with 5 different seeds and store to seperate dat files
./monte_carlo -n 65536 -r 6 | awk '{print $1, $2-3.14159265359}' > /tmp/line1.dat
./monte_carlo -n 65536 -r 45 | awk '{print $1, $2-3.14159265359}' > /tmp/line2.dat
./monte_carlo -n 65536 -r 102 | awk '{print $1, $2-3.14159265359}' > /tmp/line3.dat
./monte_carlo -n 65536 -r 93 | awk '{print $1, $2-3.14159265359}' > /tmp/line4.dat
./monte_carlo -n 65536 -r 21 | awk '{print $1, $2-3.14159265359}' > /tmp/line5.dat
#ignore line 1 as titles
#set and scale the x and y axes
#set the grid in the background
#plot each of the lines from the seperate dat files
gnuplot <<END
    set key autotitle columnhead
    set terminal pdf
    set output "graph2.pdf"
    set title "Monte Carlo Error Estimation"
    set xlabel "Iterations"
    set ylabel "Error"
    set zeroaxis
    set xrange [1:65536]
    set logscale x 4
    set for [i=0:7] xtics (1,4**i)
    set yrange [-1:1]
    set ytics (-1,-0.5,0,0.5,1)
    set grid
    plot "/tmp/line1.dat" with lines notitle, \
    "/tmp/line2.dat" with lines notitle, \
    "/tmp/line3.dat" with lines notitle, \
    "/tmp/line4.dat" with lines notitle, \
    "/tmp/line5.dat" with lines notitle
END
