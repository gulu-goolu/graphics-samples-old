//
// Created by chj on 2020/7/20.
//

#ifndef FRAMEWORK_MACROS_H
#define FRAMEWORK_MACROS_H

#define MARK_NO_COPY(CLASS)                \
  CLASS(const CLASS&) = delete;            \
  CLASS(CLASS&&) = delete;                 \
  CLASS& operator=(const CLASS&) = delete; \
  CLASS& operator=(CLASS&&) = delete;

#endif  // FRAMEWORK_MACROS_H
