import tensorflow as tf
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
tf.compat.v1.disable_eager_execution()
hello = tf.constant('hello tensorflow!')
sess = tf.compat.v1.Session()
print(sess.run(hello))
