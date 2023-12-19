package com.example.ITMOhw3.user

import org.springframework.security.core.userdetails.UserDetailsService
import org.springframework.stereotype.Service

@Service
class UserService(private val users: Users) : UserDetailsService {

    override fun loadUserByUsername(username: String): User? {
        return users.findByUsername(username)
    }
}
