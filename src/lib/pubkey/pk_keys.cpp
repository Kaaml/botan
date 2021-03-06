/*
* PK Key Types
* (C) 1999-2007 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#include <botan/pk_keys.h>
#include <botan/internal/pk_ops.h>
#include <botan/der_enc.h>
#include <botan/oids.h>
#include <botan/hash.h>
#include <botan/hex.h>

namespace Botan {

/*
* Default OID access
*/
OID Public_Key::get_oid() const
   {
   try {
      return OIDS::lookup(algo_name());
      }
   catch(Lookup_Error&)
      {
      throw Lookup_Error("PK algo " + algo_name() + " has no defined OIDs");
      }
   }

/*
* Hash of the PKCS #8 encoding for this key object
*/
std::string Private_Key::fingerprint(const std::string& alg) const
   {
   secure_vector<byte> buf = pkcs8_private_key();
   std::unique_ptr<HashFunction> hash(HashFunction::create(alg));
   hash->update(buf);
   const auto hex_print = hex_encode(hash->final());

   std::string formatted_print;

   for(size_t i = 0; i != hex_print.size(); i += 2)
      {
      formatted_print.push_back(hex_print[i]);
      formatted_print.push_back(hex_print[i+1]);

      if(i != hex_print.size() - 2)
         formatted_print.push_back(':');
      }

   return formatted_print;
   }

std::unique_ptr<PK_Ops::Encryption>
Public_Key::create_encryption_op(RandomNumberGenerator& /*rng*/,
                                 const std::string& /*params*/,
                                 const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support encryption");
   }

std::unique_ptr<PK_Ops::KEM_Encryption>
Public_Key::create_kem_encryption_op(RandomNumberGenerator& /*rng*/,
                                     const std::string& /*params*/,
                                     const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support KEM encryption");
   }

std::unique_ptr<PK_Ops::Verification>
Public_Key::create_verification_op(const std::string& /*params*/,
                                   const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support verification");
   }

std::unique_ptr<PK_Ops::Decryption>
Private_Key::create_decryption_op(RandomNumberGenerator& /*rng*/,
                                  const std::string& /*params*/,
                                  const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support decryption");
   }

std::unique_ptr<PK_Ops::KEM_Decryption>
Private_Key::create_kem_decryption_op(RandomNumberGenerator& /*rng*/,
                                      const std::string& /*params*/,
                                      const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support KEM decryption");
   }

std::unique_ptr<PK_Ops::Signature>
Private_Key::create_signature_op(RandomNumberGenerator& /*rng*/,
                                 const std::string& /*params*/,
                                 const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support signatures");
   }

std::unique_ptr<PK_Ops::Key_Agreement>
Private_Key::create_key_agreement_op(RandomNumberGenerator& /*rng*/,
                                     const std::string& /*params*/,
                                     const std::string& /*provider*/) const
   {
   throw Lookup_Error(algo_name() + " does not support key agreement");
   }

}
