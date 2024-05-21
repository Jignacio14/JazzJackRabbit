class Runnable {
public:
  virtual void start() = 0;

  virtual void join() = 0;

  virtual void stop() = 0;

  virtual bool is_alive() const = 0;

  virtual ~Runnable() {}
};
