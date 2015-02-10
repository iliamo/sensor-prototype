/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2015 Regents of the University of California.
 *
 * This file is part of next-ndnsensor (Ndn sensor Application based on Consumper / Producer API).
 *
 * next-ndnsensor is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * next-ndnsensor is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * @author Lijing Wang phdloli@ucla.edu 
 */

#include <ndn-cxx/contexts/consumer-context.hpp>
#include "consumer-callback.hpp"
#include <ndn-cxx/security/validator.hpp>

// Enclosing code in ndn simplifies coding (can also use `using namespace ndn`)
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions

// IDENTITY name of CONTROLLER
#define CONTROLLER_IDENTITY "/GOD/Confirm"  

  class Verificator
  {
  public:
    Verificator()
    {
      Name identity(CONTROLLER_IDENTITY);
      Name keyName = m_keyChain.getDefaultKeyNameForIdentity(identity);
      m_publicKey = m_keyChain.getPublicKey(keyName); 
    };
    
    bool
    onPacket(Data& data)
    {
      std::cout << "Get Data and Verify it!!" << std::endl;
      if (Validator::verifySignature(data, *m_publicKey))
      {
        std::cout << "Return Status Verified!! Name:" << data.getName() <<  std::endl;
        return true;
      }
      else
      {
        std::cout << "Return Status NOT Verified!!" << data.getName() << std::endl;
        return false;
      }
    }
    
  private:
    KeyChain m_keyChain;
    shared_ptr<PublicKey> m_publicKey;
  };

int
main(int argc, char** argv)
{

  /* 
   * cpusensorConsumer
   * get the latest cpu temperature from repo
   */
  std::string cpusensor_prefix = "/ndn/edu/ucla/lijing/cpu/temp";

  Name cpusensorPrefix(cpusensor_prefix);
      
  ConsumerCallback conCB;

  Consumer* cpusensorConsumer = new Consumer(cpusensorPrefix, SDR);
  cpusensorConsumer->setContextOption(MUST_BE_FRESH_S, true);
  //set RIGHTMOST_CHILD_S as TRUE to get the latest temperature from repo
  cpusensorConsumer->setContextOption(RIGHTMOST_CHILD_S, true);
    
  cpusensorConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
                    (InterestCallback)bind(&ConsumerCallback::processLeavingInterest, &conCB, _1));
  
  cpusensorConsumer->setContextOption(DATA_ENTER_CNTX, 
                    (DataCallback)bind(&ConsumerCallback::processData, &conCB, _1));
  
  cpusensorConsumer->setContextOption(CONTENT_RETRIEVED, 
                    (ContentCallback)bind(&ConsumerCallback::processPayload, &conCB, _1, _2));
  
//  if (argc > 1)
//    cpusensorConsumer->consume(Name(argv[1]));
//  else
  cpusensorConsumer->consume(Name(""));


  /* 
   * controllerConsumer
   * send control_command INTEREST to control the Light Component
   */
  std::string self_identity = "/user_name"; 
  std::string controllerprefix = "/ndn/edu/ucla/lijing/light/iphone";

  Name controllerPrefix(controllerprefix);
  Verificator* verificator = new Verificator();
  ConsumerCallback controllerCB;

  Consumer* controllerConsumer = new Consumer(controllerPrefix, SDR);

  controllerConsumer->setContextOption(MUST_BE_FRESH_S, true);
    
  controllerConsumer->setContextOption(INTEREST_LEAVE_CNTX, 
                    (InterestCallback)bind(&ConsumerCallback::signLeavingInterest, &controllerCB, _1));
  
//  controllerConsumer->setContextOption(DATA_ENTER_CNTX, 
//                    (DataCallback)bind(&ConsumerCallback::processData, &controllerCB, _1));
  
  controllerConsumer->setContextOption(CONTENT_RETRIEVED, 
                    (ContentCallback)bind(&ConsumerCallback::processPayload, &controllerCB, _1, _2));

  controllerConsumer->setContextOption(DATA_TO_VERIFY,
                    (DataVerificationCallback)bind(&Verificator::onPacket, verificator, _1));
  
  std::string command;
  if(argc == 3)
  {
    // if there are two arguments, the first one stands for command, the second one stands for identity_name
    self_identity = argv[2];
    command = argv[1];
  }
  else if(argc == 2)
  {
  // if there is only one argument, it stands for the command 
    command = argv[1];
  }
  else{
 // default command is "on", identity_name is /user_name
    command = "on";
  }

  controllerCB.self_identity = self_identity;
  controllerConsumer->consume(Name(command));

  return 0;
}

} // namespace ndn

int
main(int argc, char** argv)
{
  return ndn::main(argc, argv);
}
