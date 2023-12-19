package com.example.ITMOhw3.user

import org.springframework.stereotype.Service

@Service
class Users {
    val users = HashMap<String, User>()

    fun findByUsername(username: String) = users[username]

    fun save(user: User) {
        users[user.username] = user
    }

    fun getUsernames() = users.keys.stream().toArray()
}
