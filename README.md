# Multi-server, multi-queue simulation for a multi-appointment service system

This simulation is designed to enable detailed and flexible simulation of a complex queueing multi-appointment service system. It is written in C++ to optimize speed and reduce memory overhead, which is particularly important for long simulation runs with many servers.

Each 'server' represents a weekly appointment slot, and can have 1 - $\inf$ clients on their active caseload. If a server delivers appointments to each of their clients on a bi-weekly basis, they will have two clients on their active caseload.
These clients occupy a FIFO queue, where each week the client at the front of the queue gets an appointment delivered, and if they require future service, are placed at the back of the server's queue.

Servers can either be single-client servers or group servers. Single-client servers can only deliver an appointment to **1** of their clients per epoch. Group servers, on the other hand, deliver a group appointment to their clients. 
That is to say, if a group server has 4 clients on their caseload, they deliver a single appointment to all 4 of these clients at the same time each epoch.

The simulation includes the ability to model different appointment attendance probabilities and make these probabilities dependent upon the type of appointment (i.e., in-person vs. virtual). It is primarily designed to consider a scenario where there are 4 mutually exclusive appointment attendance outcomes:
1. Attendance
2. No-show
3. Last-minute cancellation
4. Cancellation with advanced notice

The waitlist for service is flexible. It can either be: (a) a single FIFO queue, where clients of all types (termed pathways in the code) occupy a single waitlist, or (b) multiple FIFO queues, one for each class/pathway.
Furthermore, in the multi-queue setting, users can pass a priority rule to set the order in which servers access the queues when onboarding new clients.
