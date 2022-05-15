#ifndef __STATE_H
#define __STATE_H
 
struct telegram;
template <class entity_type>
class State
{
public:

  virtual ~State(){}

  //this will execute when the state is entered
  virtual void Enter(entity_type*)=0;
  //this is the state's normal update function
  virtual void Execute(entity_type*)=0;
  //this will execute when the state is exited. 
  virtual void Exit(entity_type*)=0;
  virtual bool onMessage(entity_type*, const telegram&)=0;
};

#endif