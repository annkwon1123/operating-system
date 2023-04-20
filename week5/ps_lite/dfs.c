#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

// Depth-First Search Algorithm
void dfs(struct task_struct *task) {
  struct task_struct *child;
  struct list_head *list;
  printk(KERN_INFO "COMM: %-20s STATE: %ld\tPID: %d\n", task->comm, task->state, task->pid);

  /* SOLUTION 1 : list_for_each 사용할 경우 */
  list_for_each(list, &task->children) {
    /* TODO 2. 빈칸 채우기 */
    child = list_entry(list, struct task_struct, sibling);
    dfs(child);
  }
}

static int __init list_task_init(void) {

  struct task_struct *init_task;

  /* SOLUTION 1 : pid를 통해 프로세스를 불러오기 */

  /* TODO 1. init 프로세스의 pid 구조체 가져오기 (find_get_pid 사용) */
  struct pid *pid = find_get_pid(1);
  /* TODO 2. 가져온 pid를 통해 해당 프로세스의 task_struct 구조체 가져오기 (pid_task 사용) */
  init_task = pid_task(pid, PIDTYPE_PID);

  printk(KERN_INFO "INSTALL: list_tasks_dfs\n");

  dfs(init_task); // 깊이 우선 탐색을 통해 init 프로세스를 기점으로 모든
                  // 자식노드들의 프로세스를 탐색한다.
  return 0;
}

static void __exit list_task_exit(void) {
  printk(KERN_INFO "REMOVE: list_tasks_dfs\n");
}

module_init(list_task_init);
module_exit(list_task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("list tasks by dfs");
MODULE_AUTHOR("OS2022");
