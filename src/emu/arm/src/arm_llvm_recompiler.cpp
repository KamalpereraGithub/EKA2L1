/*
 * Copyright (c) 2019 EKA2L1 Team.
 * 
 * This file is part of EKA2L1 project 
 * (see bentokun.github.com/EKA2L1).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <arm/arm_llvm_recompiler.h>
#include <common/log.h>

namespace eka2l1::arm {
    llvm::JITSymbol arm_memory_manager::findSymbol(const std::string &name) {
        // Find it in link table. Runtime functions
        // Use a reference here, so we can cache all next symbols
        auto &addr = links[name];

        if (!addr) {
            // We request LLVM to find it
            addr = llvm::RTDyldMemoryManager::getSymbolAddress(name);

            if (!addr) {
                LOG_ERROR("LLVM: Symbol {} not found, linkage failed", name);
                addr = reinterpret_cast<std::uint64_t>(null);
            }
        }

        return { addr, llvm::JITSymbolFlags::Exported };
    }
}