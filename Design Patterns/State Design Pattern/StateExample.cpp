// StateExample.cpp

// Pattern Description:
// The State design pattern is a behavioral design pattern that allows an object to change its behavior based on its internal state.
// The pattern defines a set of state classes, each of which represents a specific behavior, and a context class that holds a reference to the current state.
// The context class delegates requests to the current state, which can change the context's behavior by changing the reference to a different state class.
#include <winsock2.h>

class TCPConnection;

class TCPState
{
public:
    virtual void Open(TCPConnection* t) = 0;
    virtual void Close(TCPConnection* t) = 0;
    virtual void Acknowledge(TCPConnection* t) = 0;
};

class TCPConnection
{
public:
    TCPConnection() : state_(new TCPListen()) {}
    void ActiveOpen() { state_->Open(this); }
    void PassiveOpen() { state_->Open(this); }
    void Close() { state_->Close(this); }
    void Send() { state_->Acknowledge(this); }
    void ChangeState(TCPState* s) { state_ = s; }
private:
    TCPState* state_;
};

class TCPListen : public TCPState
{
public:
    virtual void Open(TCPConnection* t)
    {
        // Send SYN, receive SYN, ACK, etc.
        t->ChangeState(new TCPEstablished());
    }
    virtual void Close(TCPConnection* t)
    {
        // Send FIN, receive FIN, ACK, etc.
        t->ChangeState(new TCPClosed());
    }
    virtual void Acknowledge(TCPConnection* /* t */) { /* Do nothing */ }
};

class TCPEstablished : public TCPState
{
public:
    virtual void Open(TCPConnection* /* t */) { /* Do nothing */ }
    virtual void Close(TCPConnection* t) {
        // Send FIN, receive FIN, ACK, etc.
        t->ChangeState(new TCPCloseWait());
    }
    virtual void Acknowledge(TCPConnection* /* t */)
    {
        // Send ACK of received data packet.
    }
};

class TCPCloseWait : public TCPState
{
public:
    virtual void Open(TCPConnection* /* t */) { /* Do nothing */ }
    virtual void Close(TCPConnection* t) {
        // Send last ACK, receive FIN, etc.
        t->ChangeState(new TCPClosed());
    }
    virtual void Acknowledge(TCPConnection* /* t */) { /* Do nothing */ }
};

class TCPClosed : public TCPState
{
public:
    virtual void Open(TCPConnection* /* t */) { /* Do nothing */ }
    virtual void Close(TCPConnection* /* t */) { /* Do nothing */ }
    virtual void Acknowledge(TCPConnection* /* t */) { /* Do nothing */ }
};

int main()
{
    TCPConnection conn;
    conn.ActiveOpen();  // Sends SYN, enters ESTABLISHED state
    conn.Send();        // Sends data, enters ESTABLISHED state
    conn.Close();       // Sends FIN, enters CLOSE_WAIT state
    conn.Send();        // Does nothing, still in CLOSE_WAIT state
    conn.Close();       // Sends last ACK, enters CLOSED state
    conn.Send();        // Does nothing, still in CLOSED state

    return 0;
}
