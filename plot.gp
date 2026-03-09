set terminal pngcairo size 1200,800 font "Arial,12"

# 1. 空間分布のプロット (Explicit)
set output "dist_explicit.png"
set title "Temperature Distribution (Explicit)"
set xlabel "x"
set ylabel "u(x,t)"
set grid
unset logscale
plot "dist_explicit.dat" index 0 using 1:2 with lines title "t=0.0", \
     "dist_explicit.dat" index 1 using 1:2 with lines title "t=0.1", \
     "dist_explicit.dat" index 2 using 1:2 with lines title "t=0.5", \
     "dist_explicit.dat" index 3 using 1:2 with lines title "t=1.0", \
     "dist_explicit.dat" index 3 using 1:3 with lines dt 2 lc rgb "black" title "Exact (t=1.0)"

# 2. 空間分布のプロット (Implicit)
set output "dist_implicit.png"
set title "Temperature Distribution (Implicit)"
plot "dist_implicit.dat" index 0 using 1:2 with lines title "t=0.0", \
     "dist_implicit.dat" index 1 using 1:2 with lines title "t=0.1", \
     "dist_implicit.dat" index 2 using 1:2 with lines title "t=0.5", \
     "dist_implicit.dat" index 3 using 1:2 with lines title "t=1.0", \
     "dist_implicit.dat" index 3 using 1:3 with lines dt 2 lc rgb "black" title "Exact (t=1.0)"

# 2.5 空間分布のプロット (Crank-Nicolson)
set output "dist_crank_nicolson.png"
set title "Temperature Distribution (Crank-Nicolson)"
plot "dist_crank_nicolson.dat" index 0 using 1:2 with lines title "t=0.0", \
     "dist_crank_nicolson.dat" index 1 using 1:2 with lines title "t=0.1", \
     "dist_crank_nicolson.dat" index 2 using 1:2 with lines title "t=0.5", \
     "dist_crank_nicolson.dat" index 3 using 1:2 with lines title "t=1.0", \
     "dist_crank_nicolson.dat" index 3 using 1:3 with lines dt 2 lc rgb "black" title "Exact (t=1.0)"

# 3. 空間刻み(dx)のコンバージェンス
set output "conv_dx.png"
set title "Grid Convergence (Spatial: dx)"
set xlabel "dx"
set ylabel "Error Norm"
set logscale xy
set format x "10^{%L}"
set format y "10^{%L}"
plot "conv_dx.dat" using 1:2 with linespoints title "Explicit L2", \
     "conv_dx.dat" using 1:3 with linespoints title "Explicit Linf", \
     "conv_dx.dat" using 1:4 with linespoints title "Implicit L2", \
     "conv_dx.dat" using 1:5 with linespoints title "Implicit Linf", \
     "conv_dx.dat" using 1:6 with linespoints title "Crank-Nicolson L2", \
     "conv_dx.dat" using 1:7 with linespoints title "Crank-Nicolson Linf"

# 4. 時間刻み(dt)のコンバージェンス
set output "conv_dt.png"
set title "Grid Convergence (Temporal: dt)"
set xlabel "dt"
set ylabel "Error Norm"
set logscale xy
set format x "10^{%L}"
set format y "10^{%L}"
plot "conv_dt.dat" using 1:2 with linespoints title "Explicit L2", \
     "conv_dt.dat" using 1:3 with linespoints title "Explicit Linf", \
     "conv_dt.dat" using 1:4 with linespoints title "Implicit L2", \
     "conv_dt.dat" using 1:5 with linespoints title "Implicit Linf", \
     "conv_dt.dat" using 1:6 with linespoints title "Crank-Nicolson L2", \
     "conv_dt.dat" using 1:7 with linespoints title "Crank-Nicolson Linf"

# 5. 安定性の確認
set output "stability.png"
set title "Stability Test (dx = \pi/20, limit dt ~ 0.0123)"
set xlabel "dt"
set ylabel "Error Norm"
unset logscale x
set logscale y
set format x "%g"
set format y "10^{%L}"
plot "stability.dat" using 1:2 with linespoints title "Explicit L2", \
     "stability.dat" using 1:4 with linespoints title "Implicit L2", \
     "stability.dat" using 1:6 with linespoints title "Crank-Nicolson L2"
