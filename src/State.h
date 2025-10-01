class State{
  public:
    void enter();
    void update();
    void exit();
    void next_state(const State);
};
