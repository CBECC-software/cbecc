/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HVACSYSTEMROOTFINDINGALGORITHM_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACSYSTEMROOTFINDINGALGORITHM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACSystemRootFindingAlgorithmFields
 *  \brief Enumeration of HVACSystemRootFindingAlgorithm's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACSystemRootFindingAlgorithmFields, )
#else
class HVACSystemRootFindingAlgorithmFields: public ::EnumBase<HVACSystemRootFindingAlgorithmFields> {
 public: 
  enum domain 
  {
Algorithm, NumberofIterationsBeforeAlgorithmSwitch,   };
  HVACSystemRootFindingAlgorithmFields()
   : EnumBase<HVACSystemRootFindingAlgorithmFields>(Algorithm) {} 
  HVACSystemRootFindingAlgorithmFields(const std::string &t_name) 
   : EnumBase<HVACSystemRootFindingAlgorithmFields>(t_name) {} 
  HVACSystemRootFindingAlgorithmFields(int t_value) 
   : EnumBase<HVACSystemRootFindingAlgorithmFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACSystemRootFindingAlgorithmFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACSystemRootFindingAlgorithmFields>::integer_value()); }
   private:
    friend class EnumBase<HVACSystemRootFindingAlgorithmFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ HVACSystemRootFindingAlgorithmFields::Algorithm, "Algorithm", "Algorithm"},
{ HVACSystemRootFindingAlgorithmFields::NumberofIterationsBeforeAlgorithmSwitch, "NumberofIterationsBeforeAlgorithmSwitch", "Number of Iterations Before Algorithm Switch"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const HVACSystemRootFindingAlgorithmFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACSystemRootFindingAlgorithmFields> OptionalHVACSystemRootFindingAlgorithmFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACSYSTEMROOTFINDINGALGORITHM_FIELDENUMS_HXX
