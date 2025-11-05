/*
    Dado una cadena C, valide si C se encuentra en notación FEN (Forsyth-Edwards Notation),
    Forsyth–Edwards Notation. FEN (Wikipedia, 2025).
*/

export enum PiecesInBoard {
    r = 'r',
    n = 'n',
    b = 'b',
    q = 'q',
    k = 'k',
    p = 'p',

    P = 'P',
    R = 'R',
    N = 'N', 
    B = 'B',
    Q = 'Q',
    K = 'K',
}

export enum TurnGame {
    b = 'b',
    w = 'w',
}

export enum Castling {
    NONE = '-',
    K = 'K',
    Q = 'Q',
    k = 'k',
    q = 'q',
}

function checkValidFEN(C: string) {

    //Obtain Chain in parts
    const fenParts = C.trim().split(/\s+/);
    const [position, turn, castling, enPassant, halfMove, fullMove] = fenParts;

    if(fenParts.length !== 6 ) {
        throw new Error('Los movimientos estan mal. No es una notacion FEN valida');
    }

    //Obtain the board rows
    const rowsInBoard = position.split('/');
    if(rowsInBoard.length !== 8) {
        throw new Error('No es un tablero valido');
    }

    for( let row of rowsInBoard) {
        let boxes = 0;
        for(let characters of row) {
            if ('12345678'.includes(characters)) {
                boxes += parseInt(characters, 10);

            } else if (Object.values(PiecesInBoard).includes(characters as PiecesInBoard)) {
                boxes += 1;
            } else {
                throw new Error(`Carácter inválido en el tablero, en la fila ${row}: ${characters}`);
            }
        };
        if (boxes !== 8) throw new Error(`No es un tablero valido`);
    }

    if(!Object.values(TurnGame).includes(turn as TurnGame)) {
        throw new Error('No son turnos validos para la notacion FEN');
    }

    if (castling !== Castling.NONE) {
        const castlingCharsUsed = new Set<string>();

        for (const castlingChar of castling) {

            if (!Object.values(Castling).includes(castlingChar as Castling)) {
                throw new Error(`Caracter de enroque inválido: "${castlingChar}"`);
            }

            // Verificar que no se repita
            if (castlingCharsUsed.has(castlingChar)) {
                throw new Error(`Enroque repetido: "${castlingChar}"`);
            }

            // Agregar a los caracteres usados
            castlingCharsUsed.add(castlingChar);
        }
    }

    if (enPassant !== '-') {
        const file = enPassant[0]; // letra a-h
        const rank = enPassant[1]; // número 3 o 6

        if (!'abcdefgh'.includes(file) || !'36'.includes(rank) || enPassant.length !== 2) {
            throw new Error(`Campo enPassant inválido: "${enPassant}"`);
        }
    }

    const halfMoveNumber = Number(halfMove);
    if (!Number.isInteger(halfMoveNumber) || halfMoveNumber < 0) {
        throw new Error(`HalfMove inválido: "${halfMove}"`);
    }

    const fullMoveNumber = Number(fullMove);
    if (!Number.isInteger(fullMoveNumber) || fullMoveNumber <= 0) {
        throw new Error(`FullMove inválido: "${fullMove}"`);
    }

    return {
        message: 'Es una nomeclatura FEN',
        data: C,
    }
}

function main(){
    console.log(checkValidFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")); // true
    console.log(checkValidFEN("8/8/8/8/8/8/8/8 w - - 0 1")); // true
    console.log(checkValidFEN("invalid FEN string")); // false
}

main();
