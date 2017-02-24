from threading import Thread, Lock
from collections import deque
import time


d = {'value': 50}


class LockManager:
    def __init__(self):
        self.lock = Lock()
        self.state = {
            'shared': deque([]),
            'exclusive': None,
            'queue': deque([])
        }

    def acquire_shared(self, thread_name, item):
        queue_front = len(self.state['queue']) and self.state['queue'][0]
        if self.state['exclusive']:
            self.state['queue'].append(item)
            return False
        elif queue_front and queue_front['name'] == thread_name and queue_front['type'] == 's':
            self.state['queue'].popleft()
            self.state['shared'].append(item)
            self.lock.release()
            return True

    def acquire_exclusive(self, thread_name, item):
        queue_front = len(self.state['queue']) and self.state['queue'][0]
        if self.state['exclusive'] or len(self.state['shared']):
            self.state['queue'].append(item)
            return False
        elif queue_front and queue_front['name'] == thread_name and queue_front['type'] == 'x':
            self.state['queue'].popleft()
            self.state['exclusive'] = item
            self.lock.release()
            return True

    def release(self, thread_name):
        for item in self.state['shared']:
            if item['name'] == thread_name:
                item['lock'].release()
                self.state['shared'] = filter(lambda l: l['name'] != thread_name, self.state['shared'])
                self.lock.release()
        if self.state['exclusive']['name'] == thread_name:
            item['lock'].release()
            self.state['exclusive'] = None
            self.lock.release()


def decrement(thread_name, d, lock_manager):
    while not lock_manager.acquire_shared(thread_name, {'name': thread_name, 'type': 's', lock: Lock()}):
        time.sleep(0.1)

    val = d['value']
    time.sleep(0.3)

    while not lock_manager.acquire_exclusive(thread_name, {'name': thread_name, 'type': 'x', lock: Lock()}):
        time.sleep(0.1)

    d['value'] = val - 5
    print "decrement val:" + str(val)
    print "decrement d['value']:" + str(d['value'])
    lock_manager.release(thread_name)


def increment(thread_name, d, lock_manager):
    while not lock_manager.acquire_shared(thread_name, {'name': thread_name, 'type': 's', lock: Lock()}):
        time.sleep(0.1)

    val = d['value']
    time.sleep(0.3)

    while not lock_manager.acquire_exclusive(thread_name, {'name': thread_name, 'type': 'x', lock: Lock()}):
        time.sleep(0.1)

    d['value'] = val + 5
    print "increment val:" + str(val)
    print "increment d['value']:" + str(d['value'])
    lock_manager.release(thread_name)

lock_manager = LockManager()

a = Thread(target=decrement, args=('a', d, lock_manager))
b = Thread(target=increment, args=('b', d, lock_manager))

a.start()
b.start()

a.join()
b.join()

print d['value']
