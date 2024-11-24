# Multi-server, multi-queue simulation for a multi-appointment service system

This simulation is designed to enable detailed and flexible simulation of a complex queueing multi-appointment service system.

Each 'server' represents a weekly appointment slot, and can have 1 - $\inf$ clients on their active caseload. If a server delivers appointments to each of their clients on a bi-weekly basis, they will have two clients on their active caseload.
These clients occupy a FIFO queue, where each week the client at the front of the queue gets and appointment delivered, and if they require future service, are placed at the back of the server's queue.

The waitlist for service is flexible. It can either be: (a) a single FIFO queue, where clients of all types (termed pathways in the code) occupy a single waitlist, or (b) multiple FIFO queues, one for each class/pathway.
Furthermore, in the multi-queue setting, users can pass a priority rule to set the order in which servers access the queues when onboarding new clients.
