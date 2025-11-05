//Implemente reconocimiento de cadenas, expresiones notación científica, ip, correo electrónico.

export const RegexConstants = {
    EMAIL: /^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$/,
    SCIENTIFIC_NOTATION: /^[-+]?(\d+(\.\d*)?|\.\d+)[eE][-+]?\d+$/,
    IP: /^(\d{1,3}\.){3}\d{1,3}$/,
}


function recognizeString (characters: string) {
    if (RegexConstants.EMAIL.test(characters)) {
        return "El string es un correo electronico"
    }

    if (RegexConstants.SCIENTIFIC_NOTATION.test(characters)) {
        return "El string es una notacion Científica";
    }

    if (RegexConstants.IP.test(characters)) {
        return "El string es una Dirección IP";
    }
    else{
        throw new Error('Cadena no pertenece a un email, notacion cinetifica o ip');
    }
}


function main(){
    console.log(recognizeString("cristian@gmail.com"));
    console.log(recognizeString("3.14e-5"));
    console.log(recognizeString("192.168.1.1"));
}

main();