function switch_mode()
{
    let mode_darklight = document.querySelector('#mode_darklight')
    let img_switch_darklight = document.querySelector('#img_switch_darklight')
    let outros_sites_seta = document.querySelectorAll('.outros_sites_seta')
    
    if (mode_darklight.getAttribute('href') == 'style_dark.css')
    {
        mode_darklight.setAttribute('href', 'style_light.css')
        img_switch_darklight.setAttribute('src', 'assets/dark_light_preto.png')
        for (let i = 0; i < outros_sites_seta.length; i++) {
            outros_sites_seta[i].setAttribute('src', 'assets/seta_preto.png')    
        }
    }
    else if (mode_darklight.getAttribute('href') == 'style_light.css')
    {
        mode_darklight.setAttribute('href', 'style_dark.css')
        img_switch_darklight.setAttribute('src', 'assets/dark_light_branco.png')
        for (let i = 0; i < outros_sites_seta.length; i++) {
            outros_sites_setsa[i].setAttribute('src', 'assets/seta_branco.png')     
        }
    }
}