#include "capteurUS.h"
// Low-level pour initialiser les capteurs US
// Et pour récupérer les valeurs de distance
int on_a_detecte = 0;

int a_t_on_detecte;

void adversaire_detecte_callback() {
    on_a_detecte = 1;

	// On acquite les interruptions pour être tranquille
	//HAL_NVIC_DisableIRQ(TIM5_IRQn);
	//HAL_NVIC_DisableIRQ(TIM8_BRK_TIM12_IRQn);

	// On a détecté quelqu'un, on dit à l'asser de s'arrêter
    send_fonction("stop()");

    // Il faut faire d'autres choses !
    init_GPIO_LED();
    while(1)
    {
        HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
        //Delay(500);
    }

}
