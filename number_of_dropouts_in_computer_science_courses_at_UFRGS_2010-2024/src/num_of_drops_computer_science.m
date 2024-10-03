%
% Caio Madeira
% github.com/caiomadeira


filename = 'CIENCIA_DA_COMPUTACAO_EVASOES_20102024.txt';

periods = {...
    '24.1', '23.2', '23.1', '22.2', '22.1', ...
    '21.2', '21.1', '20.2', '20.1', '19.2', ...
    '19.1', '18.2', '18.1', '17.2', '17.1', ...
    '16.2', '16.1', '15.2', '15.1', '14.2', ...
    '14.1', '13.P2', '13.1', '12.2', '12.1', ...
    '11.2', '11.1', '10.2', '10.1'};
    

fid = fopen(filename, 'r');
dropped = [];

while ~feof(fid)
    tline = fgetl(fid);
    
    % Verifica se a linha contem a str 'N de evadidos'
    if ~isempty(strfind(tline, 'N de Evadidos'))
        % faz o parsing da linha p/ pegar o numero apos os dois pontos
        [~, numStr] = strtok(tline, ':');
        dropped = [dropped, str2double(strtrim(numStr(2:end)))];
    end
end

fclose(fid);

%´plotagem dos grafico de barras (f(x) discreta)
figure;
bar(dropped, 'b');
set(gca, 'XTick', 1:length(periods), 'XTickLabel', periods); % rotulos do eixo X

% ajustando espacamento entre as barras
set(gca, 'TickLength', [0 0]); % remove o espaco branco entre as barras
box off; % remove a borda externa do grafico

% Adicionar título e rótulos
xlabel('Períodos', 'FontSize', 12, 'FontWeight', 'bold'); % Rótulo do eixo X com formatação
ylabel('Número de Evadidos', 'FontSize', 12, 'FontWeight', 'bold'); % Rótulo do eixo Y com formatação
title('Taxa de Evasão no Curso de Ciência da Computação na UFRGS (2010-2024.1)', ...
    'FontSize', 14, 'FontWeight', 'bold'); % Título com formatação

% Garantir que o gráfico ajuste os elementos visuais corretamente
tightInset = get(gca, 'TightInset'); 
set(gca, 'Position', [tightInset(1), tightInset(2), 1-tightInset(1)-tightInset(3), 1-tightInset(2)-tightInset(4)]);

% ajustar o tamanho da janela da figura p/ melhor visualizar as labels
set(gcf, 'Position', [100, 100, 1200, 600]);

grid on;
%disp(dropped); % visualiza o array