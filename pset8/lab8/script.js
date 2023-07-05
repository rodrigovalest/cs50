let saladaFrutas_part1 = document.getElementById("Saladinha")
let button_part1 = document.querySelectorAll(".james")

for (let i = 0; i < button_part1.length; i++)
{
    button_part1[i].addEventListener('click', function() {
        if (this != saladaFrutas_part1)
        {
            button_part1[i].style.backgroundColor = "Red"
            ativaDesativaArrayBotao(button_part1, true)
            button_part1[i].disabled = false
        }
        else
        {
            saladaFrutas_part1.style.backgroundColor = "Green"
            ativaDesativaArrayBotao(button_part1, true)
            saladaFrutas_part1.disabled = false
        }
    })
}

let inputText_part2 = document.querySelector('#input_text')
let buttonSend_part2 = document.querySelector('#send_text')

buttonSend_part2.addEventListener('click', function(event) {
    event.preventDefault()
    text_part2 = inputText_part2.value
    if (text_part2 == "James da salada de frutas" || text_part2 == "James da salada de frutas" || text_part2 == "James" || text_part2 == "james") 
    {
        buttonSend_part2.style.backgroundColor = "Green"
        buttonSend_part2.setAttribute('value', 'Acertou')   
        setTimeout(function() {inputText_part2.value = ''}, 700)
    }
    else 
    {
        buttonSend_part2.style.backgroundColor = "Red"
        buttonSend_part2.setAttribute('value', 'Errou')
        setTimeout(function() {inputText_part2.value = ''}, 700)
    }
})

function ativaDesativaArrayBotao(botao, valor)
{
    for (let i = 0; i < botao.length; i++) 
    {
        botao[i].disabled = valor
    }
}