# Inicialização
clear
reset
set key on

# Configurações de saída: inclui formato de exportação, tamanho do gráfico,
# fontes utilizadas e nome do arquivo de saída

# Exportação para o formato .png
set terminal png size 1366 768 enhanced font 'Helvetica,12'
set out './images/analiseEmpirica.png'

# Configuração do eixo horizontal
set xrange[0:100]					# Faixa de valores
# set xtics (2,4,8,16,32,64,128,256,512,1024)
# Salto entre valores
set xtic rotate by -90 scale 0		# Rotação dos rótulos
set xlabel "Tamanho do Vetor"

# Título do gráfico 
set title 'Tempo de execução das funções de ordenação'

# Configuração do eixo vertical
# set yrange[0:0.00001]					# Faixa de valores
set ylabel "Tempo (em microssegundos)"
# set format y "%.2f"

# Plotagem do gráfico
# Os dados a serem plotados constam no arquivo tempos.dat
plot './data/output/tempos.dat' using 1:2 lw 2 with lines title "Usando Processos", './data/output/tempos.dat' u 1:3 lw 2 with lines title "Sem processos"