#include <stddef.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <xdc/runtime/System.h>
#include <ti/runtime/wiring/Energia.h>

void setup();
void loop();

Void _arduino_task(UArg _task_setup, UArg _task_loop);
Void _arduino_task(UArg _task_setup, UArg _task_loop) {
 	(*(void(*)()) _task_setup)();
 	for(;;) {
 		(*(void(*)()) _task_loop)();
 		System_flush();
 		Task_yield();
 	}
}
int main() {
	Board_init();

	Task_Params taskParams;
	Task_Params_init(&taskParams);
	taskParams.priority = Task_numPriorities - 2;
	taskParams.stackSize = 0x800;
    taskParams.arg0 = (xdc_UArg) setup;
    taskParams.arg1 = (xdc_UArg) loop;
    taskParams.instance->name = (xdc_String) "arduino_task";
	Task_create(_arduino_task, &taskParams, NULL);
    BIOS_start();
	return 0;
}
