<h1 align=center>
	<b>So_Long</b>
</h1>

<p align=center>
	[The dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is a famous problem in computer science used to illustrate common issues in [concurrent programming](https://en.wikipedia.org/wiki/Concurrency_(computer_science)). The problem was originally formulated in 1965 by [Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra)

---
<div align="center">
    <img src="https://github.com/AndreLuiz-Cardoso/42_badges_utils/blob/main/philosophersm.png?raw=true"/>
</div>

---
<h2> The Dining Philosophers Problem </h2>
 <br/>
<p>Imagine a bunch of philosophers sitting around a round table with bowls of food in front of them. Each philosopher has a fork placed right in front of them, and there are just as many forks as there are philosophers. These philosophers spend their whole day doing one of three things: eating, sleeping, or thinking. But here’s the catch: to eat, a philosopher needs two forks – the one right in front of them and another one either to their right or left. And a fork can only be used by one philosopher at a time. They can pick up or put down a fork whenever they want, but they can’t start eating until they’ve got both forks in hand.</p>

<p>So, to keep things simple: when a philosopher is eating, they’re not thinking or sleeping. When they’re thinking, they’re not eating or sleeping. And when they’re sleeping, well, they’re definitely not eating or thinking.</p>
<p>Now let’s break down the idea a bit. Picture a round table with X number of philosophers sitting around it, each with a fork in front of them. A philosopher can either eat, sleep, or think. But in order to eat, they need to grab two forks: one in front of them and the one to their side (in my solution, they pick the fork to their right, but you could also make them pick the one to their left – it depends on your implementation).</p>

<p>Here’s a clearer example: imagine there are 5 philosophers sitting around the table. Philosopher 1 decides he’s hungry, so he grabs the fork in front of him and the fork to his right (which is in front of Philosopher 5). Now, Philosopher 2 and Philosopher 5 can’t eat because Philosopher 1 has taken the fork they need. This might seem obvious, but it’s the root of the challenge we’re dealing with: figuring out how to organize the eating so that everyone gets a turn without things getting stuck.</p>

<p>You might think, “Why not just make all the odd philosophers eat first, then the even ones?” Sure, that’s one way to do it, but it’s too hard-coded and takes away the fun of the project. The philosophers have to figure it out for themselves in a more dynamic way. To solve this, we’ll be using threads and creating a multithreading solution to let them manage it.</p>
<br/>
<h2> Data Races (Race Conditions) </h2>
<br/>

<p>Data races are a common issue when using multiple threads in programming. They happen when multiple threads access the same shared memory at the same time, and at least one of them is trying to write to it without proper protection. This can result in unpredictable or incorrect behavior.</p>

<p>Here are the conditions for a data race:</p>

<p>Two or more threads are accessing the same memory location.</p>
<p>At least one of these threads is trying to write to that memory.</p>
<p>There is no synchronization in place to prevent them from clashing.</p>

<h2>Mutex</h2>
<p>Now that we understand race conditions, let's look at a common solution: a mutex. A mutex acts like a lock to protect parts of your code that access shared resources. Only the thread that holds the lock can execute the code inside the lock. Other threads have to wait until the lock is released.</p>

<p>For example, if Thread #1 locks a piece of code, Thread #2 will wait until Thread #1 is finished and unlocks it. This way, we avoid race conditions. In simple terms, a race condition happens when two or more threads try to read and change a variable at the same time. This can cause incorrect values, although it doesn’t always happen.</p>

<p>Example: Imagine a function that deposits money into your bank account. If two threads try to deposit money at the same time (e.g., $300 from one thread and $200 from another), you would expect your account balance to be $500. However, without proper locking, the balance might end up incorrect.</p>

<h2>Step-by-Step Guide</h2>
<br/>
<p>Checking the Input</p>
<p>Before setting anything up, you need to make sure the program has valid input. Your program will take 4 or 5 arguments. If there are more or fewer arguments, show an error message.</p>

<p>Here's an example of input: 5 800 200 200 7</p>

<p>5 - Number of philosophers</p>
<p>800 - Time (in milliseconds) before a philosopher dies if they don’t eat</p>
<p>200 - Time it takes to eat</p>
<p>200 - Time it takes to sleep</p>
<p>7 - (Optional) Number of times each philosopher needs to eat before the program ends</p>

We should make sure:
<br/>
<p>All inputs are numbers.
Each number should be greater than 0 (except for the optional number of meals).
According to the evaluation, the maximum number of philosophers should not exceed 200.</p>
<br/>

<h2>Initialization</h2>
<br/>
<p>Because we know the maximum amount of philosophers our program can be tested with (200) and I wanted to avoid dealing with leaks, freeing, and allocating, and mainly because I wanted the performance to be faster I decided to keep all the memory on the stack and not on the heap by initializing a philo structure array, a mutex array for the forks and the program structure all in the main. From there I initialize the program variables, initialize all the mutexes for the mutex fork array, and lastly the philosophers - input variables and point the pointers to all the mutexes and the dead_flag</p>
<br/>


<h2>Thread Creation, Philosopher Routine, and Monitor</h2>
<br/>
<p>Now it’s time to create the threads and manage them. We’ll make a thread for each philosopher, plus an extra one called the "observer" to monitor everything. Each philosopher will run the philo_routine function, while the observer thread will handle the monitoring with the monitor function.</p>

<h2>Philo Routine</h2>
<br/>
<p>The philo_routine is the function that each philosopher thread will repeatedly execute. This loop continues until one of the philosophers dies (when our dead flag is set to 1). Here's how it works:</p>

<h2>The Philosophers' Cycle:</h2>
<br/>
<p>Philosophers rotate through three actions: eating, sleeping, and thinking.</p>
<p>When they eat, they aren’t thinking or sleeping.</p>
<p>When they think, they aren’t eating or sleeping.</p>
<p>When they sleep, they aren’t eating or thinking.</p>
<p>Loop Implementation:</p>

<p>For thinking, we just print a message like "Philosopher X is thinking" (where X is the philosopher number).
For sleeping, we use ft_usleep (a custom sleep function we’ll explain below) to make them sleep for the amount of time specified by the user. After sleeping, we print "Philosopher X is sleeping."
For eating, it gets more complex. First, we use pthread_mutex_lock to lock the right fork and print a message, then lock the left fork and print another message. The philosopher eats using ft_usleep, then we unlock both forks when done. We also update some variables that let the monitor know what’s happening, but that’s the basic idea.</p>

<h2>Manager</h2>
<br/>
<p>The manager thread runs continuously, keeping an eye on everything. It has two main checks, running in a loop until either a philosopher dies or they’ve all eaten the required number of meals.</p>

<p>Death Check:</p>
<br/>
<p>We make sure that the time since a philosopher's last meal hasn’t exceeded the time they can go without eating. If one has died, we set the dead flag to 1 (died of starvation), which stops all the philosopher threads.</p>

<p>Meal Completion Check:</p>
<br/>
<p>We also check if all the philosophers have eaten the necessary number of meals. If they have, we again set the dead flag to 1, ending the loop in the threads.</p>


<h2>Final Step: Destroying All Mutexes</h2>
<br/>
<p>The last step is to destroy all the mutexes you created. If you don't, they won't work properly. In this step, you should also free any memory you allocated. In this example, we didn't allocate memory, but if you did, make sure to release it.</p>
<br/>
