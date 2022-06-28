#include <linux/interrupt.h> /* IRQ interface */
#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/gpio.h>     /* wird für Zugriff auf GPIO benötigt*/


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manuel Roos <manuel.roos@stud.hslu.ch>");
MODULE_DESCRIPTION("Interrupt Kernel Modul");
MODULE_VERSION("0.1");



#define UP_PIN_BCM          5  /* wPi 21 */
#define DOWN_PIN_BCM        6  /* wPi 22 */
#define RIGHT_PIN_BCM      13  /* wPi 23 */
#define LEFT_PIN_BCM       19  /* wPi 24 */
#define PUSH_PIN_BCM       26  /* wPi 25 */


#define LED_BLUE_PIN_BCM    12 /* wPi 26 */
#define LED_GREEN_PIN_BCM   16 /* wPi 27 */
#define LED_YELLOW_PIN_BCM  20 /* wPi 28 */
#define LED_RED_PIN_BCM     21 /* wPi 29 */


static int irqNumber;

static irqreturn_t my_gpio_irq_handler(int irq, void *dev_id)
{
  /* do work here */
  printk(KERN_INFO "Button Gedrueckt \n");
  gpio_set_value(LED_BLUE_PIN_BCM, 1);  
  return IRQ_HANDLED; // IRQ was handled correctly
}



static int __init simple_init_module(void) {
  int result;
  printk(KERN_INFO "Interrupt Kernel Modul geladen.\n");
  /* A non-0 return means init_module failed; module can't be loaded.  */
  gpio_request(LED_BLUE_PIN_BCM, "LED_BLUE");
  gpio_direction_output(LED_BLUE_PIN_BCM, 0);
  gpio_set_value(LED_BLUE_PIN_BCM, 1); 
  gpio_direction_input(UP_PIN_BCM); // configure as inputx
  gpio_set_debounce(UP_PIN_BCM, 200); // debounce the button with given millisceond time 
  //IRQ STUFF
  irqNumber = gpio_to_irq(UP_PIN_BCM); // get IRQ number
  result = request_irq(irqNumber, // the interrupt number
  	my_gpio_irq_handler,
  	IRQF_TRIGGER_FALLING, // falling edge
  	"button_handler", // used in /proc/interrupts
  	NULL); // the *dev_id for shared lines
  return 0;
}


static void __exit simple_cleanup_module(void) {
  printk(KERN_INFO "Goodbye from a kernel module.\n");  
  gpio_set_value(LED_BLUE_PIN_BCM, 0);  
  gpio_free(LED_BLUE_PIN_BCM);
  free_irq(irqNumber, NULL); // free the IRQ number
  gpio_free(UP_PIN_BCM); // unexport the GPIO pin


}
  
module_exit(simple_cleanup_module);
module_init(simple_init_module);








