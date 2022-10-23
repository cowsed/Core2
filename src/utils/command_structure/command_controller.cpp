/**
 * File: command_controller.cpp
 * Desc:
 *    A CommandController manages the AutoCommands that make
 *    up an autonomous route. The AutoCommands are kept in
 *    a queue and get executed and removed from the queue
 *    in FIFO order.
 */

#include "../core/include/utils/command_structure/command_controller.h"
#include "../core/include/utils/command_structure/delay_command.h"

/**
 * Adds a command to the queue
 * @param cmd - AutoCommand to be added
 */
void CommandController::add(AutoCommand *cmd) {
  command_queue.push(cmd);
}

/**
 * Adds a command that will delay progression
 * of the queue
 * @param ms - number of milliseconds to wait
 *    before continuing execution of autonomous
 */
void CommandController::add_delay(int ms) {
  AutoCommand *delay = new DelayCommand(ms);
  command_queue.push(delay);
}

/**
 * Begin execution of the queue
 * Execute and remove commands in FIFO order
 */
void CommandController::run() {
  AutoCommand *next_cmd;
  while(!command_queue.empty()) {
    // retrieve and remove command at the front of the queue
    next_cmd = command_queue.front();
    command_queue.pop();

    // run the current command until it returns true
    while(!next_cmd -> run()) {
      vexDelay(20);
    }
    
  }
}