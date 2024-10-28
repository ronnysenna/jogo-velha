// Selecionando os elementos do DOM
const board = document.querySelectorAll('.cell');  // Todas as células do tabuleiro
const currentPlayerSpan = document.getElementById('current-player');  // Indicador do jogador atual
const resetBtn = document.getElementById('reset-btn');  // Botão de reiniciar
let currentPlayer = 'O';  // O começa primeiro
let gameState = ['', '', '', '', '', '', '', '', ''];  // Estado inicial do tabuleiro (vazio)
let gameActive = true;  // Controla o estado do jogo (ativo ou não)

// Configurações das combinações de vitória
const winningConditions = [
    [0, 1, 2],  // Linha 1
    [3, 4, 5],  // Linha 2
    [6, 7, 8],  // Linha 3
    [0, 3, 6],  // Coluna 1
    [1, 4, 7],  // Coluna 2
    [2, 5, 8],  // Coluna 3
    [0, 4, 8],  // Diagonal principal
    [2, 4, 6]   // Diagonal secundária
];

// Função para verificar o vencedor
function checkWinner() {
    for (let i = 0; i < winningConditions.length; i++) {
        const [a, b, c] = winningConditions[i];
        if (gameState[a] && gameState[a] === gameState[b] && gameState[a] === gameState[c]) {
            gameActive = false;  // Desativa o jogo, pois temos um vencedor
            setTimeout(() => alert(`O jogador ( ${gameState[a]} ) venceu!`), 10);  // Mostra o vencedor
            return;
        }
    }

    // Verifica se todas as células estão preenchidas e, se sim, declara empate
    if (!gameState.includes('')) {
        gameActive = false;  // Desativa o jogo, pois houve empate
        setTimeout(() => alert('Empate!'), 10);
    }
}

// Função para jogada da máquina (escolhe uma célula aleatória)
function jogadaMaquina() {
    if (!gameActive) return; // Verifica se o jogo ainda está ativo
    let emptyCells = [];

    // Verifica quais células estão vazias
    gameState.forEach((value, index) => {
        if (value === '') {
            emptyCells.push(index);
        }
    });

    // Escolhe uma célula vazia aleatoriamente
    const randomIndex = emptyCells[Math.floor(Math.random() * emptyCells.length)];

    // Atualiza o estado do jogo e o conteúdo da célula com a jogada da máquina ('X')
    gameState[randomIndex] = 'X';
    board[randomIndex].textContent = 'X';

    // Verifica se a máquina venceu após sua jogada
    checkWinner();

    // Muda para o jogador
    currentPlayer = 'O';
    currentPlayerSpan.textContent = currentPlayer;
}

// Função para lidar com os cliques nas células
function handleCellClick(event) {
    const clickedCell = event.target;  // A célula que foi clicada
    const cellIndex = clickedCell.getAttribute('data-index');  // Obtém o índice da célula clicada

    // Verifica se a célula já foi clicada ou se o jogo está inativo
    if (gameState[cellIndex] !== '' || !gameActive || currentPlayer === 'X') return;

    // Atualiza o estado do jogo e o conteúdo da célula com a jogada do jogador ('O')
    gameState[cellIndex] = 'O';
    clickedCell.textContent = 'O';

    // Verifica se o jogador venceu após sua jogada
    checkWinner();

    // Alterna para a jogada da máquina, se o jogo ainda estiver ativo
    if (gameActive) {
        currentPlayer = 'X';
        currentPlayerSpan.textContent = currentPlayer;
        setTimeout(jogadaMaquina, 500); // Adiciona um pequeno delay para a jogada da máquina
    }
}

// Função para reiniciar o jogo
function resetGame() {
    gameState = ['', '', '', '', '', '', '', '', ''];  // Reseta o estado do jogo
    board.forEach(cell => {
        cell.textContent = '';  // Limpa o conteúdo das células
    });
    gameActive = true;  // Reativa o jogo
    currentPlayer = 'O';  // O começa novamente
    currentPlayerSpan.textContent = currentPlayer;
}

// Adiciona um listener para cada célula do tabuleiro
board.forEach(cell => cell.addEventListener('click', handleCellClick));

// Adiciona um listener para o botão de reinício do jogo
resetBtn.addEventListener('click', resetGame);
