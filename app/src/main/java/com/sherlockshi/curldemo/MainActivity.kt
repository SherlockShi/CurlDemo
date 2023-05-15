package com.sherlockshi.curldemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.sherlockshi.curldemo.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI()
        binding.sampleText.text = curlHttpGet("https://www.tencent.com/")
    }

    /**
     * A native method that is implemented by the 'curldemo' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun curlHttpGet(url: String): String

    companion object {
        // Used to load the 'curldemo' library on application startup.
        init {
            System.loadLibrary("curldemo")
        }
    }
}