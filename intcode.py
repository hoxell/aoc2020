"""AoC IntCode machine"""
from queue import Queue
from typing import Any, Mapping


class IntCode:
    def __init__(self, instructions, allow_repeat=True):
        """IntCode machine

        Parameters
        ----------
        instructions: tuple[str, int,...]
            Instructions - (operation, operand1, operand2,...)
        allow_repeat: boolean
            Whether to allow the same instruction to be visited twice.
            Useful for detecting infinite loop if instructions are static.
        """
        self._instructions = instructions
        self._instruction_pointer = 0

        self._accumulator = 0
        self._allow_repeat = allow_repeat
        self._executed_idx = set()

        self._input_queue = Queue()
        self._output_queue = Queue()

    def reset_state(self):
        """Reset the state of the machine"""
        self._accumulator = 0
        self._instruction_pointer = 0

    def _operation_nop(self, operand, *args, **kwargs):
        self._instruction_pointer += 1

    def _operation_jmp(self, operand, *args, **kwargs):
        self._instruction_pointer += operand

    def _operation_acc(self, operand, *args, **kwargs):
        self._accumulator += operand
        self._instruction_pointer += 1

    def put(self, item):
        """Add item to (the end of) the input queue"""
        self._input_queue.put(item)

    @property
    def output_queue(self):
        """Queue object that the intcode machine pushes outputs to"""
        return self.output_queue()

    @property
    def accumulator(self) -> int:
        """Return the current value of the accumulator 'register'"""
        return self._accumulator

    def _execute_operation(self, instruction: Mapping[int, Any]):
        """Execute instruction and update machine state"""
        self.__getattribute__("_operation_" + instruction[0])(*instruction[1:])

    def run(self):
        """Run the machine

        Return
        ------
        boolean
            True if machine did not hit the stop criterion
            False if stop criterion was hit
        """
        while 0 <= self._instruction_pointer < len(self._instructions):
            self._executed_idx.add(self._instruction_pointer)
            self._execute_operation(
                self._instructions[self._instruction_pointer]
            )
            if self.stop_criterion():
                return False
        return True

    def stop_criterion(self):
        """Used to tell the machine when to stop"""

        if (
            not self._allow_repeat
            and self._instruction_pointer in self._executed_idx
        ):
            return True
        return False
