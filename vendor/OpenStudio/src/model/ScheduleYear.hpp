/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_SCHEDULEYEAR_HPP
#define MODEL_SCHEDULEYEAR_HPP

#include "ModelAPI.hpp"
#include "Schedule.hpp"

namespace openstudio {

class Date;

namespace model {

class ScheduleWeek;

namespace detail {

  class ScheduleYear_Impl;

} // detail

/** ScheduleYear is a Schedule that wraps the OpenStudio IDD object 'OS_Schedule_Year'. */
class MODEL_API ScheduleYear : public Schedule {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit ScheduleYear(const Model& model);

  virtual ~ScheduleYear() {}

  //@}

  static IddObjectType iddObjectType();

  /** @name Getters */
  //@{

  // DLM@20111018: This almost needs a RunPeriod as an argument to know the year description?
  /// Returns a vector of dates marking the end of week schedules.
  /// These dates will be in order and have the same number of elements as scheduleWeeks.
  std::vector<openstudio::Date> dates() const;

  /// Returns a vector of week schedules in the same order and with the same number of elements as dates.
  std::vector<ScheduleWeek> scheduleWeeks() const;

  //@}
  /** @name Setters */
  //@{

  /// Sets the given week schedule to be in effect until (inclusive) the date given starting 
  /// the day after the previous date marker or January 1st if no previous date marker exists. 
  /// Replaces existing scheduleWeek for same date if it exists.
  bool addScheduleWeek(const openstudio::Date& untilDate, const ScheduleWeek& scheduleWeek);

  /// Clear all week schedules from this schedule.
  void clearScheduleWeeks();

  //@}
  /** @name Other */
  //@{

  // DLM@20111018: Eventually allow "Nth day in Month" and other descriptors
  /// Returns the week schedule in effect at the given date.
  boost::optional<ScheduleWeek> getScheduleWeek(const openstudio::Date& date) const;

  //@}
 protected:
  /// @cond
  typedef detail::ScheduleYear_Impl ImplType;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class detail::ScheduleYear_Impl;

  explicit ScheduleYear(std::shared_ptr<detail::ScheduleYear_Impl> impl);

  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.ScheduleYear");
};

/** \relates ScheduleYear*/
typedef boost::optional<ScheduleYear> OptionalScheduleYear;

/** \relates ScheduleYear*/
typedef std::vector<ScheduleYear> ScheduleYearVector;

} // model
} // openstudio

#endif // MODEL_SCHEDULEYEAR_HPP

