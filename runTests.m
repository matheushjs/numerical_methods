#!/usr/bin/octave

format long

% Teste 1-b)
n = 50; % Especificação do tamanho da Matriz Pentadiagonal A.
A = pentadiag(n); % Matriz Pentadiagonal A.
x0 = zeros(1, n); % Aproximação inicial para o vetor x.
b = sum(A, 2)'; % O vetor b é o somatório das linhas de A.
x = gaussSeidel(A, x0, b) % Aplicando o método numérico de Gauss-Seidel.

% Teste 2-b)
n = 100;
A = pentadiag(n);
x0 = zeros(1, n);
b = sum(A, 2)';
x = gaussSeidel(A, x0, b)

% Teste 1-c)
n = 100;
A = pentadiag(n);
x0 = zeros(1, n);
b = 1./(1:n); % O vetor b é o inverso do índice de sua respectiva posição.
maxError = 1e-10; % Máximo erro da norma infinita em uma iteração do método.
maxIterations = 1e+99; % Nº máximo de iteração alto para garantir o erro máximo especificado.
x = gaussSeidel(A, x0, b, maxError)