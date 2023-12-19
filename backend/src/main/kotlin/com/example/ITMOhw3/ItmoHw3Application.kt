package com.example.ITMOhw3

import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication


@SpringBootApplication
class ItmoHw3Application {

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            SpringApplication.run(ItmoHw3Application::class.java, *args)
        }
    }
}