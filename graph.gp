set term pdf
set g
set xtics 5
set ytics 5
L=50
set xrange [0:L]
set yrange [0:L]

set o 'data.pdf'
plot 'results.dat' u 1:2 pt 6  title ''
