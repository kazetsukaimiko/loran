



void queuePollTaskFunction() {
    for( ;; ) {
        if (tasksInFlight()) {
            struct s = retrieveNextTask();
            
            
        }
    }
}