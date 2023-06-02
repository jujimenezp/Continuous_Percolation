set term pdf
set g

L=50
set xrange [0:L]
set yrange [0:L]

set o 'data.pdf'
plot 'results.dat' u 1:2 pt 6 ps 3 title ''
