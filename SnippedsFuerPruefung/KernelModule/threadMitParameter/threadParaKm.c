#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/gpio.h>     /* wird für Zugriff auf GPIO benötigt*/
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manuel Roos <manuel.roos@stud.hslu.ch>");
MODULE_DESCRIPTION("Mein erstes Thread Kernel Modul mit Parameter");
MODULE_VERSION("0.2");

#define LED_BLUE_PIN_BCM    12 /* wPi 26 */
#define LED_GREEN_PIN_BCM   16 /* wPi 27 */
#define LED_YELLOW_PIN_BCM  20 /* wPi 28 */
#define LED_RED_PIN_BCM     21 /* wPi 29 */


struct task_struct *task;
static int blinkMS = 500;
module_param(blinkMS , int, S_IRUGO);
MODULE_PARM_DESC(blinkMS , " BlinkFreqenz (default=500)");




static int thread(void *data){
  for(;;) {
    if (kthread_should_stop()) {
      break;
    }
    /* do something useful */
    gpio_set_value(LED_BLUE_PIN_BCM, 0);  
    msleep(blinkMS);
    gpio_set_value(LED_BLUE_PIN_BCM, 1);    
    msleep(blinkMS);

  }
  return 0;
}


static int __init simple_init_module(void) {
  printk(KERN_INFO "Erstes Kernel Thread  Modul geladen.\n");
  printk(KERN_INFO "Module loaded: ledPinNr=%d\n", blinkMS);
  /* A non-0 return means init_module failed; module can't be loaded.  */
  gpio_request(LED_BLUE_PIN_BCM, "LED_BLUE");
  gpio_direction_output(LED_BLUE_PIN_BCM, 0);
  gpio_set_value(LED_BLUE_PIN_BCM, 1);
  /* Task Stuff */	
  task = kthread_run(thread, NULL, "blinky");  
  return 0;
}

static void __exit simple_cleanup_module(void) {
  printk(KERN_INFO "Goodbye from a kernel module.\n");
  kthread_stop(task);  
  gpio_set_value(LED_BLUE_PIN_BCM, 0);  
  gpio_free(LED_BLUE_PIN_BCM);

}

module_init(simple_init_module);
module_exit(simple_cleanup_module);
