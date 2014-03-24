AudioDevice.o: AudioDevice.cpp AudioDevice.h BufferedStream.h Block.h \
 Timer.h Report.h ConcurrentQueue.h
Block.o: Block.cpp Block.h Timer.h Report.h ConcurrentQueue.h
BufferedStream.o: BufferedStream.cpp BufferedStream.h Block.h Timer.h \
 Report.h ConcurrentQueue.h
Event.o: Event.cpp Event.h Timer.h Report.h
Keyboard.o: Keyboard.cpp Keyboard.h NoteEvent.h Note.h Timer.h Report.h \
 Event.h ConcurrentQueue.h
Module.o: Module.cpp Module.h
NoteEvent.o: NoteEvent.cpp NoteEvent.h Note.h Timer.h Report.h Event.h \
 ConcurrentQueue.h
Report.o: Report.cpp Report.h
SineGenerator.o: SineGenerator.cpp SineGenerator.h Block.h Timer.h \
 Report.h ConcurrentQueue.h Module.h Note.h NoteEvent.h Event.h Heap.h
Synthesizer.o: Synthesizer.cpp Report.h Timer.h Synthesizer.h Keyboard.h \
 NoteEvent.h Note.h Event.h ConcurrentQueue.h AudioDevice.h \
 BufferedStream.h Block.h SineGenerator.h Module.h Heap.h Task.h \
 WorkerThread.h Thread.h
Task.o: Task.cpp Task.h Module.h
Thread.o: Thread.cpp Thread.h Report.h
Timer.o: Timer.cpp Timer.h Report.h
WorkerThread.o: WorkerThread.cpp WorkerThread.h Thread.h Task.h Module.h
main.o: main.cpp Keyboard.h NoteEvent.h Note.h Timer.h Report.h Event.h \
 ConcurrentQueue.h Synthesizer.h
